import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';
import { AppRoutingModule } from './app-routing.module';
//import { CommonModule } from '@angular/common';

/* Module Components */
import { AppComponent } from './app.component';

/* Service */
// // import { LanguageService } from './services/language.service';
// // import { ThemeService } from './services/theme.service';

/* Page Components */
import { HomePageComponent } from './pages/home/home.page.component';

/* ERROR Pages */
import { ErrorPageComponent } from './pages/error/error.page.component';
import { SidenavComponent } from './components/base/sidenav/sidenav.component';
import { HeaderComponent } from './components/header/header.component';


@NgModule({
  imports: [
    /* default */
    BrowserModule,
    //CommonModule,
    /* Routing */
    AppRoutingModule,
  ],
  declarations: [
    AppComponent,

    /* Module Components */

    /* Page Components */
    HomePageComponent,
    ErrorPageComponent,
    SidenavComponent,
    HeaderComponent,
  ],
  providers: [
    //* LanguageService,    << provided in root
    //* ThemeService,       << provided in root
  ],
  bootstrap: [AppComponent]
})
export class AppModule { }
