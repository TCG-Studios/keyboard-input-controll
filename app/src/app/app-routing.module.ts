import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';

// import {AppResolver} from './app.resolver';

/* Page Components */
import { HomePageComponent } from './pages/home/home.page.component';


/* ERROR Page */
import { ErrorPageComponent } from './pages/error/error.page.component';

const routes: Routes = [
  /* redirects as alias (or pages that are N/A at the Moment) */
  { path: 'cfg', pathMatch: 'full',redirectTo: '/error?code=501&source=\/cfg' },
  { path: 'impressum', pathMatch: 'full',redirectTo: '/error?code=501&source=\/impressum' },
  { path: 'dev/home', pathMatch: 'full',redirectTo: '/error?code=423&source=\/dev\/home' },
  { path: 'lession/routing', pathMatch: 'full',redirectTo: '/error?code=501&source=\/lession\/routing' },
  { path: 'lession/module_components', pathMatch: 'full',redirectTo: '/error?code=501&source=\/lession\/module_components' },

  /* Routs to Pages */
  { path: 'home', component: HomePageComponent },

  //Error Page
  { path: 'error', component: ErrorPageComponent },

  /* redirects if anything is wrong */
  { path: '', pathMatch: 'full', redirectTo: 'home' },
  { path: '**', pathMatch: 'full', redirectTo: '/error?code=404' },
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
