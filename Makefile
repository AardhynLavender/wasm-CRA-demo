src/module.mjs: src/main.cpp
	emcc \
		--no-entry src/main.cpp -o src/module.mjs \
		--pre-js src/locateFile.js  \
		-lembind \
		-s ENVIRONMENT='web'  \
		-s EXPORT_NAME='createModule'  \
		-s USE_ES6_IMPORT_META=0 
	mv src/module.wasm public/module.wasm
	
.PHONY: clean
clean:
	rm public/module.wasm src/module.mjs
	