import { Component } from '@angular/core';
import { Router } from '@angular/router'

@Component({
  selector    : 'HomePageComponent',
  templateUrl : './home.page.component.html',
  styleUrls   : ['./home.page.component.less'],
  host        : { class: 'HomePageComponent' }
})
export class HomePageComponent {

  constructor(
    public router: Router
  ){
  }
  //Router
  public navigate(event: Event, path: string): void {
    event.preventDefault();
    this.router
      .navigate([path])
      .then();
  }
}
