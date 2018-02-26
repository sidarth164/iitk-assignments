project: main.tex
	pdflatex main
main.tex: body.pdf results.pdf citations.bib
	pdflatex main
	bibtex main
	pdflatex main
body.pdf:body.tex
	pdflatex body
results.pdf:results.tex
	pdflatex results
tables.pdf:tables.tex
	pdflatex tables
results.tex: tables.pdf graph1.pdf graph2.pdf
	pdflatex results
graph1.pdf:graph1.csv graph1.gnu
	gnuplot graph1.gnu
graph2.pdf:graph2.gnu graph2.csv
	gnuplot graph2.gnu
.PHONY: clean clean-all
clean:
	-rm -f *.log *.bak *.aux *.bbl *.blg *.idx *.toc *.out *~
clean-all:
	-rm -f *.dvi *.log *.bak *.aux *.bbl *.blg *.idx *.ps *.eps *.pdf *.toc *.out *~ *.sta
