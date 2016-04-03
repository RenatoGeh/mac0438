f_exs = exercises
e_compile = pdflatex -shell-escape $(f_exs).tex


all: exs

no_viewer:
	make clean; \
	$(e_compile);

exs:
	make clean; \
	$(e_compile); \
	zathura $(f_exs).pdf

.PHONY: clean
clean:
	rm *.aux *.bbl *.bcf *.blg *.log *.out *.run.xml *.toc;
	rm -rf _minted-report

