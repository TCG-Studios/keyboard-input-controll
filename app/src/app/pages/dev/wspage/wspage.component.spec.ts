import { ComponentFixture, TestBed } from '@angular/core/testing';

import { WSPageComponent } from './wspage.component';

describe('WSPageComponent', () => {
  let component: WSPageComponent;
  let fixture: ComponentFixture<WSPageComponent>;

  beforeEach(() => {
    TestBed.configureTestingModule({
      declarations: [WSPageComponent]
    });
    fixture = TestBed.createComponent(WSPageComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
