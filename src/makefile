all:
	java -jar ../beaver-cc-0.9.9.jar -d parser parser/parser.beaver
	jflex -d parser parser/lexer.jlex
	javac dice/*.java expr/*.java flowcontrol/*.java functions/*.java parser/*.java util/*.java

clean:
	rm -rf dice/*.class
	rm -rf expr/*.class
	rm -rf flowcontrol/*.class
	rm -rf functions/*.class
	rm -rf parser/*.class
	rm -rf util/*.class
