import { Component, ViewChild } from '@angular/core';

import { LanguageService } from 'src/app/services/language.service';
import { EventService } from 'src/app/services/event.service';

import { SidenavItems } from 'src/app/models/sidenav.model';


@Component({
  selector: 'SidenavComponent',
  templateUrl: './sidenav.component.html',
  styleUrls: ['./sidenav.component.less'],
  host        : { class: 'SidenavComponent' }
})
export class SidenavComponent {
  showFiller = false;
  sidenavItems = SidenavItems;

  @ViewChild('sidenav') sidenav: any;

  constructor(
    public lang          : LanguageService,
    private eventService : EventService,
  ) {
    this.eventService.buttonClick$
    .subscribe(() => {  // TODO unsub??? => ngOnDestroy
      this.doSomething();
    })
  }

  doSomething() {
    this.sidenav.toggle()
  }
}
