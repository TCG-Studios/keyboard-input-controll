import { NgModule }                         from '@angular/core';

import { MatIconModule }                    from '@angular/material/icon';
import { MatCardModule }                    from '@angular/material/card';
import { MatListModule }                    from '@angular/material/list';
import { MatMenuModule }                    from '@angular/material/menu';
import { MatSortModule }                    from '@angular/material/sort';
import { MatTabsModule }                    from '@angular/material/tabs';
import { MatBadgeModule }                   from '@angular/material/badge';
import { MatInputModule }                   from '@angular/material/input';
import { MatTableModule }                   from '@angular/material/table';
import { MatButtonModule }                  from '@angular/material/button';
import { MatDialogModule }                  from '@angular/material/dialog';
import { MatIconRegistry }                  from '@angular/material/icon';
import { MatRippleModule }                  from '@angular/material/core';
import { MatSelectModule }                  from '@angular/material/select';
import { MatDividerModule }                 from '@angular/material/divider';
import { MatStepperModule }                 from '@angular/material/stepper';
import { MatTooltipModule }                 from '@angular/material/tooltip';
import { MatCheckboxModule }                from '@angular/material/checkbox';
import { MatSnackBarModule }                from '@angular/material/snack-bar';
import { MatPaginatorModule }               from '@angular/material/paginator';
import { MatFormFieldModule }               from '@angular/material/form-field';
import { MatDatepickerModule }              from '@angular/material/datepicker';
import { MatProgressBarModule }             from '@angular/material/progress-bar';
import { MatSlideToggleModule }             from '@angular/material/slide-toggle';
import { MatButtonToggleModule }            from '@angular/material/button-toggle';
import { MatAutocompleteModule }            from '@angular/material/autocomplete';
import { MatProgressSpinnerModule }         from '@angular/material/progress-spinner';

// import { MatMomentDateModule }              from '@angular/material-moment-adapter';
import { MatGridListModule }                from "@angular/material/grid-list";
import { MatSliderModule }                  from "@angular/material/slider";
import { MatExpansionModule }               from '@angular/material/expansion';

//New
import {MatToolbarModule} from '@angular/material/toolbar';
import {MatSidenavModule} from '@angular/material/sidenav';

@NgModule({
    exports : [
        MatIconModule,
        MatCardModule,
        MatListModule,
        MatMenuModule,
        MatSortModule,
        MatTabsModule,
        MatBadgeModule,
        MatInputModule,
        MatTableModule,
        MatButtonModule,
        MatDialogModule,
        MatRippleModule,
        MatSelectModule,
        MatDividerModule,
        MatStepperModule,
        MatTooltipModule,
        MatCheckboxModule,
        MatGridListModule,
        MatSliderModule,
        MatSnackBarModule,
        MatPaginatorModule,
        MatFormFieldModule,
        MatDatepickerModule,
        MatProgressBarModule,
        MatSlideToggleModule,
        MatButtonToggleModule,
        MatAutocompleteModule,
        MatProgressSpinnerModule,
        MatExpansionModule,
        // MatMomentDateModule,

        //New
        MatToolbarModule,
        MatSidenavModule,
    ],
    providers: [
        MatIconRegistry,
    ],
})
export class AppMaterialModule {
    constructor(public matIconRegistry: MatIconRegistry) {
        matIconRegistry.registerFontClassAlias('fontawesome', 'fa');
    }
}