import { Component } from '@angular/core';
import { Router } from '@angular/router';

import { EventService } from 'src/app/services/event.service';

@Component({
  selector    : 'HeaderComponent',
  templateUrl : './header.component.html',
  styleUrls   : ['./header.component.less'],
  host        : { class: 'HeaderComponent' },
})
export class HeaderComponent {

  constructor(
    public router: Router,
    private eventService: EventService,
  ){
  }

  public navigate(event: Event, path: string,): void {
    event.preventDefault();

    this.router
      .navigate([path])
      .then();
  }

  toggleNav(){
    this.eventService.emitButtonClick();  // TODO adjustment when service changes (see service TODO)
  }
}
