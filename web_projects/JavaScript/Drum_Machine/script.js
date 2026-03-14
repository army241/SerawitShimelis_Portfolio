const pads = document.querySelectorAll(".drum-pad")

pads.forEach(function(pad){

pad.addEventListener("click",function(){

const key = pad.innerText
playSound(key)

})

})

document.addEventListener("keydown",function(event){

playSound(event.key.toUpperCase())

})

function playSound(key){

const audio = document.getElementById(key)

if(!audio) return

audio.currentTime = 0
audio.play()

const name = audio.parentElement.id

document.getElementById("display").innerText = name

}