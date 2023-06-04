import { EventEmitter, Injectable } from '@angular/core';
import { BehaviorSubject } from 'rxjs/internal/BehaviorSubject';
import { Observable } from 'rxjs/internal/Observable';

import { supportedLanguages, ILanguages, defaultLanguage } from '../models/supportedLanguages.model';

@Injectable()
export class LanguageService {
  protected activeLanguageSubject : BehaviorSubject<string>;
  public languageChanged = new EventEmitter<void>();

  private translations       : { [key: string]: any } = {};
  private language           : ILanguages[0] = defaultLanguage;
  private supportedLanguages : ILanguages = supportedLanguages;

  public get languageObservable() : Observable<string> {
    return this.activeLanguageSubject.asObservable();
  }

  // * constructor **************************************************
  constructor() {
    // Initialisierung des BehaviorSubject für die aktive Sprache
    this.activeLanguageSubject = new BehaviorSubject<string>(this.getLanguage());
    // Laden der Übersetzungsdateien
    this.loadTranslations();
  }
  
  // * functions ****************************************************
  private loadTranslations() {
    //! Annahme: Die JSON-Dateien sind im geforderten Ordner und haben entsprechende Namen
    supportedLanguages.forEach(lang => {
      // Laden der Übersetzungsdatei
      const translation = require(`../assets/lang/${lang}.json`);
      this.translations[lang] = translation;
    });
  }

  public changeLanguage(language: string) {
    // Überprüfung, ob die Sprache unterstützt wird
    if (this.supportedLanguages.includes(language)) {
      this.language = language;
      // Auslösen des languageChanged-Ereignisses
      this.languageChanged.emit();
    } else {
      console.error('Unsupported language:', language);
    }
  }

  public getTranslation(path: string): string {
    const translation = this.translations[this.language];
  
    if (translation) {
      // Split the key into nested keys if there are dots present
      const nestedKeys = path.split('.');
      let nestedTranslation = translation;
  
      for (const nestedKey of nestedKeys) {
        // Check if the nested translation for the current key exists
        if (nestedTranslation && nestedTranslation[nestedKey]) {
          nestedTranslation = nestedTranslation[nestedKey];
        } else {
          // Return the original key if any nested translation is missing
          return path;
        }
      }
      // Return the final nested translation
      return nestedTranslation;
    }
    // Return the original key if translation is missing for the selected language
    return path;
  }
  
  //! Not for nested obj
  // public getTranslation(key: string): string {
  //   const translation = this.translations[this.language];
  //   if (translation && translation[key]) {
  //     return translation[key];
  //   }
  //   return key;
  // }
  // Alias für getTranslation
  public get(key: string): string {
    return this.getTranslation(key);
  }

  private getLanguage(): string {
    // Auslesen der Spracheinstellung aus dem Local Storage
    // Standardwert falls keine Spracheinstellung vorhanden ist
    this.language = localStorage.getItem('language') || defaultLanguage;
    // Speichern der Spracheinstellung im Local Storage (falls erforderlich)
    localStorage.setItem('language', this.language);
    return this.language;
  }
}

// @Injectable()
// export class languageService {

//   protected activeLanguageSubject: BehaviorSubject<any>;
//   public languageChanged = new EventEmitter<object>();
  
//   protected language = localStorage.getItem("language")
  
//   public get themeObservable(): Observable<ILanguages> {
//     return this.activeLanguageSubject.asObservable();
//   }

//   constructor() {
//     this.activeLanguageSubject = new BehaviorSubject<any>(this.getLanguage());
//   }

//   public changeLanguage(language:ILanguages){
//     this.language = language
//     this.languageChanged.emit()
//   }
  
//   private getLanguage() {
//     this.language = localStorage.getItem("language") ? localStorage.getItem("language") : 'en'
//     localStorage.setItem("language",this.language? this.language : "en")
//     return this.language;
//   }
// }


