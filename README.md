# mediakeys

Detect "play", "next", and "prev" keys globally in Node.js.

```
npm install mediakeys
```

(Linux requires `apt-get install dbus`, dbus-devel, or equivalent.)

then

```
var mediakeys = require('mediakeys').listen();
mediakeys.on('play', function () {
	console.log('play');
})
mediakeys.on('next', function () {
	console.log('next');
})
mediakeys.on('back', function () {
	console.log('back');
})
```

That easy! To test globally on any platform:

```
$ npm install -g mediakeys
$ mediakeys
connected
play
next
back
...
```

## Source

Code for this library is sourced from a few locations:

## Windows

<http://www.codeguru.com/cpp/w-p/system/keyboard/article.php/c5655/Using-Multimedia-Keyboard-Keys-in-Your-Own-Program.htm> (?? licensed)

## OS X

<https://github.com/msfeldstein/MediaKeyHosts> (?? licensed)

### Linux

<https://github.com/Shouqun/node-dbus> (MIT licensed)

## License

All original code licensed under MIT.