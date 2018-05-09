// Initialize Firebase
//The project has been deleted in firebase
//fill in your own config info 
var config = {
  apiKey: "",
  authDomain: "",
  databaseURL: "",
  projectId: "",
  storageBucket: "",
  messagingSenderId: ""
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