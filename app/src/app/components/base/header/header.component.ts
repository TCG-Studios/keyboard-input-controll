import { Component } from '@angular/core';
import { Router } from '@angular/router';

@Component({
  selector    : 'HeaderComponent',
  templateUrl : './header.component.html',
  styleUrls   : ['./header.component.less'],
  host        : { class: 'HeaderComponent' },
})
export class HeaderComponent {

  constructor(
    public router: Router
  ){
  }

  public navigate(event: Event, path: string,): void {
    event.preventDefault();

    this.router
      .navigate([path])
      .then();
  }

  toggleNav(){
    console.info("toggle nav")
  }
}
