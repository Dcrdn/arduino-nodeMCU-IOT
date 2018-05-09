// Initialize Firebase
//The project has been deleted in firebase
//fill in your own config info 
var config = {
  apiKey: "AIzaSyCvaF8XIzgYIs1o-iLHIf1UWVnAttA1Z6E",
  authDomain: "ejemploarduino-64e24.firebaseapp.com",
  databaseURL: "https://ejemploarduino-64e24.firebaseio.com",
  projectId: "ejemploarduino-64e24",
  storageBucket: "ejemploarduino-64e24.appspot.com",
  messagingSenderId: "1088871159027"
};
firebase.initializeApp(config);

$(document).ready(function(){
  var database = firebase.database();
  var ledStatus;

  database.ref().on("value", function(snap){
    ledStatus = snap.val().ledStatus;
    cerca = snap.val().cerca;
    humedad = snap.val().humedad;
    temperatura = snap.val().temperatura;

    if(ledStatus == 1){
      $(".lightStatus").text("Luz prendida");
    } else {
      $(".lightStatus").text("Luz apagada");
    }

        document.getElementById("temp").innerHTML = temperatura;
        document.getElementById("hum").innerHTML = humedad;

    if(cerca==1){
            document.getElementById("cerca").innerHTML = "Verdadero";

    }else{
            document.getElementById("cerca").innerHTML = "Falso";
    }

  });

  $(".lightButton").click(function(){
    var firebaseRef = firebase.database().ref().child("ledStatus");

    if(ledStatus == 1){
      firebaseRef.set(0);
      ledStatus = 0;
    } else {
      firebaseRef.set(1);
      ledStatus = 1;
    }
  });
});