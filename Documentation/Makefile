all: Ultraschall\ Install\ and\ Release\ Notes.html

Ultraschall\ Install\ and\ Release\ Notes.html: Ultraschall\ Install\ and\ Release\ Notes.md Ultraschall\ Install\ and\ Release\ Notes.css Makefile
	pandoc --from=markdown --to=html --standalone --self-contained --css=Ultraschall\ Install\ and\ Release\ Notes.css --output=Ultraschall\ Install\ and\ Release\ Notes.html Ultraschall\ Install\ and\ Release\ Notes.md

clean:
	rm Ultraschall\ Install\ and\ Release\ Notes.html

