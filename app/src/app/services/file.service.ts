import { Injectable } from '@angular/core';

import { environment } from 'src/environments/environment';

@Injectable({
  providedIn: 'root'
})
export class FileService {
  private xhr: XMLHttpRequest = new XMLHttpRequest();

  protected username = environment.secrets.fileService.username
  protected password = environment.secrets.fileService.passwort
  
  constructor() {
    this.testfunc()
  }

  /**
   * Behandelt die Antwort der XMLHttpRequest-Anfrage.
   * @param xhr Die XMLHttpRequest-Instanz.
   * @param resolve Die Funktion zum Auflösen des Promises.
   * @param reject Die Funktion zum Ablehnen des Promises.
   * @param func Die Funktion, um die Antwort zu verarbeiten.
   * @param args Optionale Argumente für die Funktion.
   */
  private handleResponse(xhr: XMLHttpRequest, resolve: Function, reject: Function, func: Function, args?: any[]): void {
    if (xhr.readyState === 4) {
      if (xhr.status === 200) {
        if (args) {
          resolve(func.apply(null, [xhr, ...args]));
        } else {
          resolve(func(xhr));
        }
      } else {
        reject(new Error('Failed to load file.'));
      }
    }
  }

  /**
   * Lädt eine Datei von einem gegebenen Pfad.
   * @param filePath Der Pfad zur Datei.
   * @returns Ein Promise, das das Ergebnis der Dateiladung enthält.
  */
  public loadFile(filePath: string): Promise<any> {
    return new Promise((resolve, reject) => {
      const func = (xhr: XMLHttpRequest) => {
        return JSON.parse(xhr.responseText);
      };

      this.xhr.onreadystatechange = () => {
        this.handleResponse(this.xhr, resolve, reject, func);
      };

      this.xhr.open('GET', filePath, true);
      this.xhr.send();
    });
  }

  /**
   * Lädt eine Datei von einer gesicherten URL mit Benutzername und Passwort.
   * @deprecated
   * @param url Die gesicherte URL mit Benutzername und Passwort.
   * @returns Promise das das Ergebnis der Dateiladung enthält.
   */
  public loadFileFromSecureURL(url: string): Promise<any> {
    return new Promise((resolve, reject) => {
      const xhr = new XMLHttpRequest();

      xhr.onreadystatechange = () => {
        this.handleResponse(xhr, resolve, reject, (xhr: XMLHttpRequest) => {
          return xhr.responseText;
        });
      };

      xhr.open('GET', url, true);
      xhr.setRequestHeader('Authorization', 'Basic ' + btoa(this.username + ':' + this.password));
      xhr.send();
    });
  }


  /**
   * Liefert eine Liste aller Dateien eines bestimmten Typs aus einem Ordner.
   * @param folderPath Der Pfad zum Ordner.
   * @param fileType Der gewünschte Dateityp.
   * @returns Ein Promise, das die Liste der Dateien enthält.
   */
  public getFilesFromFolder(folderPath: string, fileType: string): Promise<string[]> {
    return new Promise((resolve, reject) => {
      const func = (xhr: XMLHttpRequest, fileType: string) => {
        console.info(xhr)
        console.info(xhr.responseText)
        const files: string[] = [];
        const response = JSON.parse(xhr.responseText);
        for (const file of response.files) {
          if (file.endsWith(fileType)) {
            files.push(file);
          }
        }
        return files;
      };

      this.xhr.onreadystatechange = () => {
        this.handleResponse(this.xhr, resolve, reject, func, [fileType]);
      };

      this.xhr.open('GET', folderPath, true);
      this.xhr.send();
    });
  }

  private testfunc() {
    var r = this.getFilesFromFolder("./assets/lang/","json")
    r.then(data => {
      // Das Ergebnis der Dateiladung ist im `data`-Parameter enthalten
      console.log('result:', data);
      // Weitere Verarbeitung der geladenen Daten
    })
    .catch(error => {
      // Ein Fehler ist aufgetreten
      console.error('Fehler beim result:', error);
      // Behandlung des Fehlers
    });
  }
}
