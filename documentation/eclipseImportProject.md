# Importieren des Projekts in Eclipse

## Vorbemerkung

Sie sollten eine Eclipse-Version mit den _C/C++ Development Tools (CDT)_ verwenden, siehe z.B. [hier](https://www.eclipse.org/downloads/packages/release/luna/r/eclipse-ide-cc-developers).

Im Pool können Sie die vorinstallierte Eclipse-Version _Eclipse JEE 4.6.2 (Neon)_ verwenden, in der CDT bereits vorinstalliert ist.

In einigen alten Eclipse-Versionen (z.B. Mars) werden teilweise Fehler im Code gekennzeichnet, die eigentlich keine sind, sondern aus Problemen mit dem Eclipse-Indexer resultieren. Diese können durch entsprechende [Konfiguration](./eclipseConfig.md) behoben werden.

## Importieren und Einrichten eines Git-Projektes

Unter `File - Import` können Sie den Assistenten zum Importieren von Projekten starten. Wählen Sie als Projekttyp `Git - Projects from Git` aus. Anschließend können Sie entweder ein bereits existierendes lokales Repository auswählen, wenn Sie Ihr Projekt bereits geklont haben, oder das Projekt direkt über dessen URL klonen.

Danach müssen Sie das Projekt in Eclipse noch einrichten: 

* Wählen Sie dazu `Import using the New Project Wizzard` aus.
* Im nächsten Schritt muss `C++ - Makefile Project with Existing Code` ausgewählt werden. 
* Sie können dann das lokale Verzeichnis mit Ihrem Projekt auswählen.
* Wählen Sie danach die passende Toolchain. Für Linux ist das z.B. `Linux GCC`, für Mac OS `MacOSX GCC`.

## Hinzufügen von Build-Targets

Um die im Projekt definierten Programme erstellen zu können, benötigen Sie Zugriff auf die entsprechenden Ziele im Makefile. Um diesen zu bekommen, gehen Sie bitte wie folgt vor:

* Öffnen Sie die Datei `Makefile` in Eclipse.
* Öffnen Sie die `C++`-Perspektive mit `Window - Perspektive - Open Perspektive - Other - C++`
* Öffnen Sie die "Outline View" über `Window - Show View - Outline`. Es werden unter anderem die im Makefile definierten Ziele dargestellt, erkennbar durch die Zielscheiben-Symbole.
* Klicken Sie mit der rechten Maustaste auf das Ziel `mkfs.myfs` und wählen Sie `Add build Target`. Bestätigen Sie im folgenden Dialog mit `OK`.
* Verfahren Sie analog für die Ziele `mount.myfs`, `unittest`, `clean` und ggf. `all`.
* Wenn Sie nun auf die "Build Targets View" wechseln über `Window - Show View - Build Targets` sehen Sie die gerade erstellten Ziele. Ein Ziel lässt sich mit einem Doppelklick erstellen.
* Nach dem Erstellen erscheint (wenn fehlerfrei übersetzt und gelinkt wird) ein Programm unter den Projektdateien im Verzeichnis `Binaries`. Dieses können Sie dann über einen Rechtsklick und `Run as - Local C++ Application` starten.



