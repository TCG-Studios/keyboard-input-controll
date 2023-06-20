import { EventEmitter, Injectable } from '@angular/core';
import { BehaviorSubject } from 'rxjs/internal/BehaviorSubject';
import { Observable } from 'rxjs/internal/Observable';

import { FileService } from './file.service';
import { supportedLanguages, ILanguages, defaultLanguage } from '../models/supportedLanguages.model';

@Injectable({
  providedIn: 'root'
})
export class LanguageService {
  protected activeLanguageSubject : BehaviorSubject<string>;
  public languageChanged = new EventEmitter<void>();

  public fileService = new FileService()

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
    console.info("constructor of LanguageService")
  }
  
  // * functions ****************************************************
  private loadTranslations() {
    //! Annahme: Die JSON-Dateien sind im geforderten Ordner und haben entsprechende Namen
    supportedLanguages.forEach(lang => {
      // Laden der Übersetzungsdatei
      //! nicht Runtime
      const translation = require(`src/assets/lang/${lang}.json`);
      console.info(translation)
      this.translations[lang] = translation;
    });
  }

  public changeLanguage(language: string) {
    // Überprüfung, ob die Sprache unterstützt wird
    if (this.supportedLanguages.includes(language)) {
      this.language = language
    } else {
      this.language = defaultLanguage
      console.error('Unsupported language:', language);
      console.warn('Change to default language:', defaultLanguage);
    }
    // Speichern der Spracheinstellung im Local Storage (falls erforderlich)
    localStorage.setItem('language', this.language);
    this.languageChanged.emit();
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
  // Alias für getTranslation
  public get(key: string): string {
    return this.getTranslation(key);
  }

  private getLanguage(): string {
    // Auslesen der Spracheinstellung aus dem Local Storage
    // Standardwert falls keine Spracheinstellung vorhanden ist
    const localStorageLanguage = localStorage.getItem('language') || "defaultLanguage";
    this.changeLanguage(localStorageLanguage)
    return this.language;
  }
}