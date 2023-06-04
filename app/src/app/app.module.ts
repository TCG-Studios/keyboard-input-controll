import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';
import { AppRoutingModule } from './app-routing.module';

/* Module Components */
import { AppComponent } from './app.component';

/* Service */
import { LanguageService } from './services/language.service';
import { ThemeService } from './services/theme.service';

/* Page Components */
import { HomePageComponent } from './pages/home/home.page.component';

/* ERROR Pages */
//import { ErrorPageComponent }               from './pages/error/error.page.component';


@NgModule({
  imports: [
    /* default */
    BrowserModule,
    /* Routing */
    AppRoutingModule,
  ],
  declarations: [
    AppComponent,

    /* Module Components */

    /* Page Components */
    HomePageComponent,
  ],
  providers: [
    LanguageService,
    ThemeService,
  ],
  bootstrap: [AppComponent]
})
export class AppModule { }
