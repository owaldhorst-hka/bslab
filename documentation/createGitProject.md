# Anlegen eines GIT-Projekts für Ihr Team

Sie können den [Gitlab-Server der Fakultät](https://iz-gitlab-01.hs-karlsruhe.de) oder GitHub verwenden. Dort kann ein Team-Mitglied ein Projekt anlegen und die übrigen Team-Mitglieder einladen. 

Im folgenden gehen wir davon aus, dass das Projekt unter folgender URL zu finden ist: 

	https://github.com/nutzer/projektname.git 

Das Template kann dann wie folgt importiert werden:
	
	git clone --bare https://github.com/owaldhorst-hka/bslab.git
	cd bslab.git
	git push --mirror https://github.com/nutzer/projektname.git
	cd ..
	rm -rf bslab.git
