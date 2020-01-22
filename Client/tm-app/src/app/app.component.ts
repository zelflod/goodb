import { Component } from '@angular/core';

import { TokenService } from './shared/token.service';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})

export class AppComponent {
  title = 'Task manager';

  public constructor(private tokenService: TokenService){
    this.tokenService.init({
      apiBase: 'http://127.0.1.1:9090',
      apiPath: 'api',
      globalOptions: {
        headers: {
          'Content-Type': 'application/json',
        }
      }
    })
  }
}
