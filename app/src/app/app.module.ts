import { NgModule         } from '@angular/core'            ;
import { BrowserModule    } from '@angular/platform-browser';
import { AppRoutingModule } from './app-routing.module'     ;
import { CommonModule } from '@angular/common';
import { BrowserAnimationsModule } from '@angular/platform-browser/animations';


/* Module Components */
import { AppComponent } from './app.component';

/* Submodules */
import { AppMaterialModule  } from './modules/material.module' ;

/* APP Components */
import { HeaderComponent } from './components/base/header/header.component';
import { SidenavComponent } from './components/base/sidenav/sidenav.component';

/* Page Components */
import { HomePageComponent } from './pages/home/home.page.component';
import { SettingsPageComponent } from './pages/settings/settings.page.component';
import { ErrorPageComponent } from './pages/error/error.page.component';
import { WSPageComponent } from './pages/dev/wspage/wspage.component';

@NgModule({
  imports: [
    /* default */
    BrowserModule,
    BrowserAnimationsModule,
    CommonModule,

    /* Routing */
    AppRoutingModule,
    
    /* Submodules */
    AppMaterialModule,
  ],
  exports:[
    
  ],
  declarations: [
    AppComponent,
    
    /* Components */
    HeaderComponent,
    SidenavComponent,

    /* Page Components */
    HomePageComponent,
    SettingsPageComponent,
    ErrorPageComponent,
    WSPageComponent,
  ],
  providers: [
    //* some services are provided in root directly
  ],
  bootstrap: [AppComponent]
})
export class AppModule { }
