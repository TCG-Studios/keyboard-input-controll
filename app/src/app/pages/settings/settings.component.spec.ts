import { ComponentFixture, TestBed } from '@angular/core/testing';

import { SettingsPageComponent } from './settings.component';

describe('SettingsComponent', () => {
  let component: SettingsPageComponent;
  let fixture: ComponentFixture<SettingsPageComponent>;

  beforeEach(() => {
    TestBed.configureTestingModule({
      declarations: [SettingsPageComponent]
    });
    fixture = TestBed.createComponent(SettingsPageComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
