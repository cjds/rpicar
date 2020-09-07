console.log("MAR");

function keyListener(ev: KeyboardEvent) {
	console.log(ev);
}

document.onkeypress = keyListener;
