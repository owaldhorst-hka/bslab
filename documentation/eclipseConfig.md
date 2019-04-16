# Konfiguration von älteren Eclipse-Versionen

Der Eclipse-Indexer, der für die korrekte Darstellung des Codes benötigt wird, hat in älteren Eclipse-Versionen teilweise Probleme mit dem Labor-Template. Diese lassen sich wie nachfolgend beschrieben beheben.

## Korrekte Darstellung der FUSE-Funktionen
Wenn in der Eclipse-IDE FUSE-Funktionen als fehlerhaft gekennzeichnet werden, kann das wie folgt behoben werden:

* Rechtsklick auf Ihr Projekt, dann `Properties` wählen.
* Unter `C/C++ General - Indexer`: 'Index unused headers as C files' und 'Index source and header files opens in editor' einschalten.
* `fuse.h` öffnen

## Korrekte Darstellung von C++11
Wenn in der Eclipse-IDE Bestandteile von C++ 11 als fehlerhaft gekennzeichnet werden, kann das wie folgt behoben werden:

* Rechtsklick auf Ihr Projekt, dann `Properties` wählen.
* Auswahl von `C/C++ General - Preprocessor Include Paths, Macros etc.`.
* Reiter Providers auswählen, Zeile `compiler settings` für den benutzten Compiler auswählen
* Hinzufügen von `-std=c++11` zu `Command to get compiler specs`. Das sollte dann in etwa so aussehen :`${COMMAND} -E -P -v -dD "${INPUTS}" -std=c++11`
* Änderungen durch `Apply` anwenden.
* Ausführen von `Project - C/C++ Index - Rebuild`
