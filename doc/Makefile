all:
	@echo "make [html | txt | pdf | web | manual]"

html: nametag.html
txt: nametag.txt nametag_install.txt
pdf: nametag.pdf
web: web.html web_install.html web_user.html web_api.html web_about.html
manual: nametag.html nametag.txt nametag_install.txt nametag_readme.txt
manual: nametag_bindings_java_readme.txt nametag_bindings_perl_readme.txt nametag_bindings_python_readme.txt
	cp nametag.txt ../MANUAL
	cp nametag.html ../MANUAL.html
	cp nametag_install.txt ../INSTALL
	cp nametag_readme.txt ../README
	cp nametag_bindings_java_readme.txt ../bindings/README.JAVA
	cp nametag_bindings_perl_readme.txt ../bindings/README.PERL
	cp nametag_bindings_python_readme.txt ../bindings/README.PYTHON

nametag.html: nametag.t2t *.t2t
	./txt2tags -t html -C not_web.conf $<

nametag_%.html: nametag_%.t2t *.t2t
	./txt2tags -t html -C not_web.conf -C strip_level.conf -o- $< | sed '/^<H2>=*<\/H2>$$/d' >$@

web.html: nametag.t2t *.t2t
	./txt2tags -t html -C web.conf -o $@ $<

web_%.html: nametag_%.t2t *.t2t
	./txt2tags -t html -C web.conf -C strip_level.conf -o- $< | sed '/^<H2>=*<\/H2>$$/d' >$@

nametag.txt: nametag.t2t *.t2t
	./txt2tags -t txt -C not_web.conf --no-toc --no-enum-title -o- $< | sed '/^$$/{3d;$$d}' >$@

nametag_%.txt: nametag_%.t2t *.t2t
	./txt2tags -t txt -C not_web.conf -C strip_level.conf --no-toc --no-enum-title -o- $< | sed '/^$$/{3d;$$d}' >$@

nametag.tex: nametag.t2t *.t2t
	./txt2tags -t tex -C not_web.conf $<

nametag.pdf: nametag.tex *.sty
	TEXINPUTS=.:$(DIR): pdflatex $<
	TEXINPUTS=.:$(DIR): pdflatex $<

.PHONY: clean
clean:
	rm -f *.aux *.dvi *.html *.log *.pdf *.out *.tex *.toc *.txt
