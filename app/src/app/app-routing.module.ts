import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';

// import {AppResolver} from './app.resolver';

/* Page Components */
import { HomePageComponent } from './pages/home/home.page.component';
import { SettingsPageComponent } from './pages/settings/settings.component';

/* ERROR Page */
import { ErrorPageComponent } from './pages/error/error.page.component';

/* TEST Components */
import { SidenavComponent } from './components/base/sidenav/sidenav.component';
import { WSPageComponent  } from './pages/dev/wspage/wspage.component'        ;

const routes: Routes = [
  /* redirects as alias (or pages that are N/A at the Moment) */
  { path : 'cfg'                      , pathMatch: 'full',redirectTo: '/error?code=501&source=\/cfg'                        },
  { path : 'impressum'                , pathMatch: 'full',redirectTo: '/error?code=501&source=\/impressum'                  },
  { path : 'dev/home'                 , pathMatch: 'full',redirectTo: '/error?code=423&source=\/dev\/home'                  },

  /* Routs to Test Pages */
  { path: 'test/nav', component: SidenavComponent },
  { path: 'dev/ws'  , component: WSPageComponent  },

  /* Routs to Main Pages */
  { path : 'home'    , component: HomePageComponent     },
  { path : 'settings', component: SettingsPageComponent },

  /* Routs to Error Pages */
  { path: 'error', component: ErrorPageComponent },

  /* redirects if anything is wrong */
  { path: ''  , pathMatch: 'full', redirectTo: 'home'            },
  { path: '*' , pathMatch: 'full', redirectTo: '/error?code=404' },
  { path: '**', pathMatch: 'full', redirectTo: '/error?code=404' },
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
