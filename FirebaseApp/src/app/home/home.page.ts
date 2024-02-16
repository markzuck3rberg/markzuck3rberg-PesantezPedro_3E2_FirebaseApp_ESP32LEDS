import { Component } from '@angular/core';
import { Firestore, doc, setDoc } from '@angular/fire/firestore';
import { getDoc } from 'firebase/firestore';

@Component({
  selector: 'app-home',
  templateUrl: 'home.page.html',
  styleUrls: ['home.page.scss'],
})
export class HomePage {
  private tableled1: any;
  private tableled2: any;
  private tableled3: any;
  private tableled4: any;

  constructor(private db: Firestore) {
    this.saveStateData();
  }

  estadoLed1: boolean = false;
  estadoLed2: boolean = false;
  estadoLed3: boolean = false;
  estadoLed4: boolean = false;

  async encender(led: string) {
    let tableled: any;
    let estadoLed: boolean;

    if (led === 'LED1') {
      tableled = this.tableled1;
      estadoLed = this.estadoLed1;
    } else if (led === 'LED2') {
      tableled = this.tableled2;
      estadoLed = this.estadoLed2;
    } else if (led === 'LED3') {
      tableled = this.tableled3;
      estadoLed = this.estadoLed3;
    }else if (led === 'LED4') {
      tableled = this.tableled4;
      estadoLed = this.estadoLed4;
    }

    tableled = doc(this.db, 'controlLED/' + led);
    estadoLed = true;
    await setDoc(tableled, { encender: estadoLed });
    this.actualizarEstado(led, estadoLed);
  }

  async apagar(led: string) {
    let tableled: any;
    let estadoLed: boolean;

    if (led === 'LED1') {
      tableled = this.tableled1;
      estadoLed = this.estadoLed1;
    } else if (led === 'LED2') {
      tableled = this.tableled2;
      estadoLed = this.estadoLed2;
    } else if (led === 'LED3') {
      tableled = this.tableled3;
      estadoLed = this.estadoLed3;
    }else if (led === 'LED4') {
      tableled = this.tableled4;
      estadoLed = this.estadoLed4;
    }

    tableled = doc(this.db, 'controlLED/' + led);
    estadoLed = false;
    await setDoc(tableled, { encender: estadoLed });
    this.actualizarEstado(led, estadoLed);
  }

  async saveStateData() {
    const docref1 = doc(this.db, 'controlLED', 'LED1');
    const docref2 = doc(this.db, 'controlLED', 'LED2');
    const docref3 = doc(this.db, 'controlLED', 'LED3');
    const docref4 = doc(this.db, 'controlLED', 'LED4');

    const snap1 = await getDoc(docref1);
    const snap2 = await getDoc(docref2);
    const snap3 = await getDoc(docref3);
    const snap4 = await getDoc(docref4);

    if (snap1.exists()) {
      this.estadoLed1 = snap1.data()['encender'];
    }

    if (snap2.exists()) {
      this.estadoLed2 = snap2.data()['encender'];
    }//a

    if (snap3.exists()) {
      this.estadoLed3 = snap3.data()['encender'];
    }

    if (snap4.exists()) {
      this.estadoLed4 = snap4.data()['encender'];
    }
  }

  actualizarEstado(led: string, estado: boolean) {
    if (led === 'LED1') {
      this.estadoLed1 = estado;
    } else if (led === 'LED2') {
      this.estadoLed2 = estado;
    } else if (led === 'LED3') {
      this.estadoLed3 = estado;
    }else if (led === 'LED4') {
      this.estadoLed4 = estado;
    }
  }

  getColor(estado: boolean): string {
    return estado ? 'success' : 'danger';
  }
}


