import { Component } from '@angular/core';

@Component({
  selector    : 'HeaderComponent',
  templateUrl : './header.component.html',
  styleUrls   : ['./header.component.less'],
  host        : { class: 'HeaderComponent' },
})
export class HeaderComponent {

  toggleNav(){
    console.info("toggle nav")
  }
}
