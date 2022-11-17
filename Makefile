all: clean tree23
tree23:
	@echo " "
	@echo "==============================="
	@echo "|         ÁRVORE-2 3          |"
	@echo "==============================="
	@echo "Compilando o biblioteca Arvore de Busca Binária. Programa 23Tree"
	gcc Tree23.c Tree23.h Tree23Test.c -o tree23
	chmod +x tree23
clean:
	@echo " "
	@echo "==============================="
	@echo "|    REMOVENDO PROGRAMAS      |"
	@echo "==============================="
	@echo "Removendo os arquivos compilados"
	rm -f tree23