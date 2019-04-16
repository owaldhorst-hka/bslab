# Entwickeln mit Docker

_Diese Dokumentation basiert auf [Arbeiten von Henning Häcker](https://github.com/hacker-h/bsuebung-docker)._

## Vorbemerkung

Falls man (auf Linux oder Mac OS) FUSE nicht nativ installieren möchte oder (auf Microsoft Windows 10) FUSE nicht nativ verfügbar ist, kann mit Hilfe des Werkzeugs _Docker_ eine leichtgewichtige virtuelle Maschine - genannt _Container_ erzeugt werden, die alles Wichtige für dieses Labor enthält:

* Vorinstallierte FUSE-Bibliotheken
* Werkzeuge für Übersetzen und Fehlersuche
* bash inkl. wichtiger Kommandozeilen-Werkzeuge
* Möglichkeit zum Entwickeln mit Hilfe von CLion/Windows über eine Remote Toolchain

## Installation von Docker

Zur Installation von Docker auf den verschiedenen Plattformen hat Herr Häcker eine ausführliche [Anleitung](https://github.com/hacker-h/bsuebung-docker) geschrieben.

## Starten eines MyFS-Containers

Um einen Container für Ihr MyFS-Projekt zu starten, wechseln Sie in Ihrem Projekt in das Verzeichnis [docker](./docker). Dort finden Sie ein Script [runDocker.sh](./docker/runDocker.sh). Evtl. müssen Sie dieses Script einmalig mit dem Kommando

	chmod +x runDocker.sh
	
ausführbar  machen. Danach kann der Container mit dem Kommando

	./runDocker.sh
	
gestartet werden. Mit dem Container startet eine bash Shell im Verzeichnis `/MyFS`, in das (über ein Docker-Volume) ihre Projektdateien eingebunden werden. In diesem Verzeichnis können Sie beispielsweise den Code übersetzen, Programme ausführen, debuggen, usw.. 

Dir Container wird beendet, wenn Sie in der Kommandozeile `exit` eingeben.

## Entwickeln mit einer CLion Remote Toolchain

Kostenlose Lizenzen für die Nutzung von CLion (und anderen Jetbrains-Produkten) zu Ausbildungszwecken gibt es in [Ilias](https://ilias.hs-karlsruhe.de/goto.php?target=crs_99205&client_id=HSKA).

Die IDE CLion unterstütz die Entwicklung von Programmen auf entfernten (_remote_) Rechnern, also anderen Rechnern, als dem, auf dem die IDE selber ausgeführt wird. Dabei werden Übersetzen, Programmausführung und Debugging über eine _Remote Toolchain_ auf einem entfernten Rechner gestartet und die Ausgaben jeweils in der lokalen IDE angezeigt. Für den Entwickler fühlt es sich so an, als würde alles auf einem einzigen Rechner passieren.

Da der MyFS-Docker-Container nach außen wie ein eigener Rechner aussieht, bietet es sich an, diesen für die Remote-Entwicklung zu nutzen. Beispielsweise könnte man die CLion IDE auf seinem Windows-Rechner betreiben und mit der Remote Toolchain auf den MyFS-Container zugreifen. Dazu muss der MyFS-Container wie oben beschrieben gestartet werden.

Unter CLion muss [wie hier beschrieben](https://www.jetbrains.com/help/CLion/remote-projects-support.html) eine Remote Toolchain eingerichtet werden. Dafür benötigen Sie die folgenden Informationen:

* Host: `localhost`
* Port: `22222`
* User Name: `root`
* Password: `root`

Hinweis: Nach einem Neustart des Containers muss ggf. das CMake-Projekt neu geladen werden.