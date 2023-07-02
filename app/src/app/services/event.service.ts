import { Injectable } from '@angular/core';
import { Subject } from 'rxjs';

@Injectable({
  providedIn: 'root'
})
export class EventService {
  private buttonClickSubject = new Subject<void>();

  buttonClick$ = this.buttonClickSubject.asObservable();

  emitButtonClick() {
    this.buttonClickSubject.next();
  }
}

// TODO make service more modular to other stuff in the future (maybe with a model that can function as a config)