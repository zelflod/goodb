import { Injectable } from "@angular/core";
import { Response } from "@angular/http";

import { Observable, throwError } from "rxjs";
import {catchError, map} from "rxjs/operators";
import { TokenService } from "./token.service";

import { User } from "./user.model";

@Injectable()

export class AuthService{
  currentUserData = {};
  signedIn = false;
  authUrl = 'auth';

  public constructor(private tokenService: TokenService){ }

  public signUp(user: User): Observable<Response>{
    // return this.tokenService.registerAccount(user as any).pipe(
    //   catchError(this.handleErrors)
    // )
    let url = `${this.authUrl}/sign_up`;
    return this.tokenService.post(url, user).pipe(
        catchError(this.handleErrors),
        map((response: Response) => {
          this.signedIn = true;
          this.currentUserData = {
            email: response.json().email,
            uid: response.json().uid
          };
          return response
        })
    )
  }
  
  public signIn(uid: string, password: string): Observable<Response>{
    let signInData = {
      email: uid,
      password: password
    };

    // return this.tokenService.signIn(signInData).pipe(
    //   catchError(this.handleErrors)
    // )
    let url = `${this.authUrl}/sign_in`;
    return this.tokenService.post(url, signInData).pipe(
        catchError(this.handleErrors),
        map((response: Response) => {
          this.signedIn = true;
          this.currentUserData = {
            email: response.json().email,
            uid: response.json().uid
          };
          return response
        })
    )
  }

  public signOut(): Observable<Response>{
    // return this.tokenService.signOut().pipe(
    //   catchError(this.handleErrors)
    // )
    let url = `${this.authUrl}/sign_out`;
    return this.tokenService.post(url, this.currentUserData).pipe(
        catchError(this.handleErrors),
        map((response: Response) => {
          this.signedIn = false;
          this.currentUserData = null;
          return response
        })
    )
  }

  public userSignedIn(): boolean{
    // return this.tokenService.userSignedIn();
    return this.signedIn;
  }
  
  private handleErrors(error: Response){
    console.log("ERROR => ", error);
    return throwError(error);
  }


}