src/module.mjs: src/main.cpp
	emcc src/main.cpp -o src/module.mjs \
		--pre-js src/locateFile.js  \
		-lembind \
		-s DISABLE_DEPRECATED_FIND_EVENT_TARGET_BEHAVIOR \
		-s USE_SDL=2 \
		-s ENVIRONMENT='web'  \
		-s EXPORT_NAME='createModule'  \
		-s USE_ES6_IMPORT_META=0 
	mv src/module.wasm public/module.wasm
	
.PHONY: clean
clean:
	rm public/module.wasm src/module.mjs
	