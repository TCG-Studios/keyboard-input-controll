import { Component } from '@angular/core';

@Component({
  selector: 'SidenavComponent',
  templateUrl: './sidenav.component.html',
  styleUrls: ['./sidenav.component.less'],
  host        : { class: 'SidenavComponent' }
})
export class SidenavComponent {
  showFiller = false;
}
