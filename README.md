# Makecode-Erweiterung zur Aktivierung der Energieverwaltung auf dem Calliope mini 3

Diese Erweiterung fügt alle Blöcke hinzu, die du brauchst, um weniger Strom in deinem Programm zu verbrauchen, wenn du den  [Calliope mini](https://calliope.cc) verwendest.

Diese Erweiterung kann nützlich sein, wenn du Batteriestrom sparen möchtes, z.B. während einer Datenprotokollierung.

## Einsatz

### Den Calliope mini in einen Energiesparmodus versetzen 💤

Der ``||power.lowPowerRequest||`` Block fordert den Calliope mini auf, bei nächster Gelegenheit in den Stromsparmodus zu wechseln, z. B. wenn die aktuelle Code-Operation abgeschlossen werden konnte, oder innerhalb von ``||basic.pause(ms)||``.

```blocks
input.onButtonPressed(Button.B, function () {
    power.lowPowerRequest()
})
```

Du kannst ``||power.lowPowerRequest(LowPowerMode.Wait)||`` senden. Dann wird der Calliope mini auch eine Pause einlegen, bis ein Ereignis mit voller Leistung eintritt.

Der Block ``||power.lowPowerPause(ms)||`` fordert den Calliope mini auf, für eine bestimmte Zeit in Millisekunden zu schlafen.

Im Energiesparmodus schläft das Calliope mini, und dein Programm wird angehalten. Wenn das micro:bit in den Vollstrommodus erwacht, wird dein Programm an der Stelle fortgesetzt, an der es angehalten wurde.

Du kannst die Blöcke ``||power.lowPowerEnable(LowPowerEnable.Prevent)||`` und ``||power.lowPowerEnable(LowPowerEnable.Allow)||`` verwenden, um Stromsparanfragen zu blockieren, bis der Code zwischen den beiden Blöcken beendet ist. Es wird erwartet, dass diese Blöcke in Paaren verwendet werden.


```blocks
basic.forever(function () {
    power.lowPowerEnable(LowPowerEnable.Prevent)
    led.plot(2, 2)
    basic.pause(1000)
    led.unplot(2, 2)
    led.plot(2, 1)
    basic.pause(1000)
    led.unplot(2, 1)
    power.lowPowerEnable(LowPowerEnable.Allow)
    power.lowPowerRequest()
})
```

### Aufwecken des Calliope mini in den Vollstrommodus ⏰

Um das Calliope mini in den Vollstrommodus zu versetzen, müssen du ein Ereignis definieren, das den Weckruf auslöst.

Du kannst den Calliope mini aufwecken, wenn eine Taste oder ein Pin gedrückt wird. In diesem Beispiel wird das micro:bit aufgeweckt, wenn die Taste A oder Pin 0 gedrückt wurde.

```blocks
power.fullPowerOn(FullPowerSource.A)
power.fullPowerOn(FullPowerSource.P0)
```

Du kannst den Calliope mini auch in einem bestimmten Zeitintervall in Millisekunden aufwecken. In diesem Beispiel wird der Calliope mini jede Minute aufgeweckt und zeigt einen Smiley auf dem Bildschirm

```blocks
power.fullPowerEvery(60000, function () {
    basic.showIcon(IconNames.Happy)
    basic.clearScreen()
    power.lowPowerRequest()
})
```

## Lizenz
This software made available under the MIT open source license.
Forked from a repository from microbit foundation.

[SPDX-License-Identifier: MIT](/LICENSE)


#### Metadata (used for search, rendering)

* for PXT/calliope
* for PXT/calliopemini

<script src="https://makecode.com/gh-pages-embed.js"></script><script>makeCodeRender("{{ site.makecode.home_url }}", "{{ site.github.owner_name }}/{{ site.github.repository_name }}");</script>
