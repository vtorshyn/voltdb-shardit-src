VOLTDB_ROOT=$(shell dirname `pwd`)/voltdb-3.7
VOLTDB=$(VOLTDB_ROOT)/bin/voltdb

CATALOG_FILE=voltdb-chatter.jar
DDL_FILE=$(shell pwd)/scheme/dbchat_scheme.sql
DEPLOYMENT_FILE=$(shell pwd)/scheme/deployment.xml
JAVAC=javac
#/opt/java/jdk1.7.0_25/bin/javac
JCLASS_PATH="$(CLASS_PATH):$(VOLTDB_ROOT)/voltdb/*"
all: compile-java-procs compile-ddl

compile-java-procs:
	$(JAVAC) -cp $(JCLASS_PATH) java/vposter/procedures/AddMessage.java \
		java/vposter/procedures/GetHistory.java \
		java/vposter/procedures/GetStats.java
compile-ddl: compile-java-procs
	$(VOLTDB) compile --classpath=./java/ -o $(CATALOG_FILE) $(DDL_FILE)
clean:
	rm -rf *.jar ./java/vposter/procedures/*.class *.html *.txt ./voltdbroot/* log statement-plans
run:
	export PID=`jps | grep -i voltdb | awk '{ print $$1 }'` && if [ "$${PID}" ]; then echo "Volt PID is: $${PID}"; else ($(VOLTDB) create catalog $(CATALOG_FILE) host $(shell hostname) deployment $(DEPLOYMENT_FILE) > run-log &); sleep 5s; fi
stop:
	export PID=`jps | grep -i voltdb | awk '{ print $$1 }'` && if [ "$${PID}" ]; then echo $${PID};kill $${PID}; fi