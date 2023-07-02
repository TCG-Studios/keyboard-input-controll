import { Component }                from '@angular/core';
import { Router, ActivatedRoute }   from '@angular/router';
import { IError }                   from 'src/app/models/error.model';

import { LanguageService } from 'src/app/services/language.service';

@Component({
  selector    : 'ErrorPageComponent',
  templateUrl : './error.page.component.html',    // TODO turn it in to ng Materials >> make it pretty 
  styleUrls   : ['./error.page.component.less'],
  host        : { class: 'ErrorPageComponent' }
})
export class ErrorPageComponent{
  public errorCode           : string = "404"
  public error               : IError = {name: "Error", description:"Error"};
  public hasErrorDescription : boolean = true;
  public showDetails         : boolean = false;
  public source              : string | boolean = false;

  constructor(
    public router          : Router,
    private activatedRoute : ActivatedRoute,
    public lang            : LanguageService,
  ){
    // console.log(activatedRoute.snapshot.queryParamMap.get("code"))
    activatedRoute.queryParams.subscribe(queryParms => {
      // Get current error code from URL path
      this.errorCode = activatedRoute.snapshot.queryParamMap.get("code") ?? this.errorCode;
      this.source = activatedRoute.snapshot.queryParamMap.get("source") || false;
    });
    this.setErrorObj()
  }
  //Router
  public navigate(event: Event, path: string): void {
    event.preventDefault();
    this.router
      .navigate([path])
      .then();
  }

  setErrorObj(){
    //Set error obj for component
    this.error = {
      name: this.lang.get("HTTPSerror."+this.errorCode+".name"),
      description: this.lang.get("HTTPSerror."+this.errorCode+".description")
    }
  }

  details(){
    this.showDetails = !this.showDetails;
  }
}
