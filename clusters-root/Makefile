CWD=$(shell pwd)

ACTIVE_ROOT=$(CWD)/exec-root/active
PASSIVE_ROOT=$(CWD)/exec-root/passive
CATALOG_DIR=$(CWD)/catalog
voltdb=$(shell which voltdb)

all: 
	@echo "$(MAKE) start-active-node - will start active node"
	@echo "$(MAKE) start-passive-node - will start passive node"
	@echo "$(MAKE) run - will compile catalog file and will run: active,passive and dragent"
run : compile-cat run-master
compile-cat: create-runtime-dirs
	cd $(CATALOG_DIR) && $(voltdb) compile ../ddl/ddl.sql

create-runtime-dirs:
	mkdir -p $(ACTIVE_ROOT) \
	    $(PASSIVE_ROOT) \
	    $(CATALOG_DIR)

run-master: compile-cat create-runtime-dirs start-active-node start-passive-node start-dragent

start-active-node:
	cd $(ACTIVE_ROOT) && $(voltdb) create --admin=6001 --client=6005 --http=6010 --replication=6015 --host=localhost:6020 ../../catalog/catalog.jar

start-passive-node:
	cd $(PASSIVE_ROOT) && $(voltdb) create --admin=6021 --client=6025 --http=6030 --replication=6035 --host=localhost:6040 --replica ../../catalog/catalog.jar

start-dragent:
	echo "DR AGENT TASK IS NOT IMPLEMENTED YET"
