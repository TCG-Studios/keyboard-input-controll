import { AfterViewInit, ChangeDetectorRef, Component, OnInit } from '@angular/core';

//import { ThemeService } from './services/theme.service';


@Component({
  selector    : 'AppComponent',
  templateUrl : './app.component.html',
  styleUrls   : ['./app.component.less'],
  host        : { class: 'AppComponent' }
})
export class AppComponent implements OnInit, AfterViewInit {
  title = 'app';
  //currentTheme = this.themeService.getTheme()

  //* Constructor ***************************************************
  constructor(
    //public themeService: ThemeService,
    // public cdRef = ChangeDetectorRef; // FIXME ChangeDetectorRef
  ){
  }

  //* Angular *******************************************************
  ngOnInit(): void {
    // this.themeService
    //   .ThemeChanged
    //   .subscribe( () => this.updateTheme())
    console.log("ngOnInit app Comp")
  }

  ngAfterViewInit(): void {
    //Called after ngAfterContentInit when the component's view has been initialized. Applies to components only.
    //Add 'implements AfterViewInit' to the class.
    // this.cdRef.detectChanges()
  }

  //* Functions *****************************************************
  // updateTheme(){
  //   this.currentTheme = this.themeService.getTheme()
  //   // Trigger Change Detection to update other components
  //   this.cdRef.detectChanges()
  // }


  NavTestFunc():void {
    console.log("test")
  }
}
