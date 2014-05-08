# use

```
npm install mediakeys
```

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

## notes

```
windows

http://www.codeguru.com/cpp/w-p/system/keyboard/article.php/c5655/Using-Multimedia-Keyboard-Keys-in-Your-Own-Program.htm
http://yabb.jriver.com/interact/index.php?topic=15649.0;wap2

osx

https://github.com/msfeldstein/MediaKeyHosts

linux

http://bluesock.org/~willkg/blog/dev/gnome_media_keys.html
```

## license

gotta look these up