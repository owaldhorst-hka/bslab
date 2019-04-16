# Anlegen eines GIT-Projekts für Ihr Team

Sie können den [Gitlab-Server der Fakultät](https://iz-gitlab-01.hs-karlsruhe.de) verwenden. Auf diesem kann ein Team-Mitglied ein Projekt anlegen und unter „Settings – Members“ die übrigen Team-Mitglieder einladen. 

Im folgenden gehen wir davon aus, dass das Projekt vom Nutzer `wyxz1234` angelegt wurde, `projektname` heißt und unter folgender URL zu finden ist: 

	https://iz-gitlab-01.hs-karlsruhe.de/wxyz1234/projektname.git 

Das Template kann dann wie folgt importiert werden:
	
	git clone --bare https://iz-gitlab-01.hs-karlsruhe.de/IWI-I/bslab.git
	cd bslab.git
	git push --mirror https://iz-gitlab-01.hs-karlsruhe.de/wxyz1234/projektname.git
	cd ..
	rm -rf bslab.git
