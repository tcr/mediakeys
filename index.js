#!/usr/bin/env node

var path = require('path');
var spawn = require('child_process').spawn;
var EventEmitter = require('events').EventEmitter;
var Parser = require('newline-json').Parser;

function runProgram (cmd) {
	var e = new EventEmitter();
	var proc = spawn(cmd, []);
	// proc.stdout.pipe(process.stdout);
	// proc.stderr.pipe(process.stderr);
	// proc.on('exit', function (code) {
	// 	console.error('exited with code', code);
		// process.exit(code);
	// })

	var parser = new Parser();
	proc.stdout.pipe(parser);
	parser.on('data', function (data) {
		if (data && data.action) {
			e.emit(data.action);
		}
	})
	return e;
}

function listen () {
	if (process.platform == 'darwin') {
		var cmd = path.join(path.dirname(require('bindings')('binding').path), 'keylistener');
		return runProgram(cmd);

	} else if (process.platform == 'win32') {
		var cmd = path.join(path.dirname(require('bindings')('binding').path), 'keylistener.exe');
		return runProgram(cmd);
	} else {
		throw new Error('unsupported platform', process.platform)
	}
}

exports.listen = listen;

if (require.main == module) {
	// demo
	var e = listen();
	e.on('connected', function () {
		console.log('connected');
	})
	e.on('play', function () {
		console.log('play');
	})
	e.on('next', function () {
		console.log('next');
	})
	e.on('back', function () {
		console.log('back');
	})
}
