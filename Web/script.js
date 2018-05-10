//esto lo llenaremos con la información que podemos obtener de firebase:Da click en la opción de Añade a tu web dentro de tu proyecto.

var config = {
  apiKey: "",
  authDomain: "",
  databaseURL: "",
  projectId: "",
  storageBucket: "",
  messagingSenderId: ""
};

//esto sirve para empezar a usar firebase y hacer un setup de nuestra configuración
firebase.initializeApp(config);

//ese código se estará cargando en todo momento, cada instante se estará verificando y corriendo sus funciones
$(document).ready(function(){
  //declaro que estare usando una db de firebase
  var database = firebase.database();
  //las variables que estaré usando
  var ledStatus; //el led que manejare con un boton
  var cerca;//si detecto a alguien con mi sensor
  var humedad;//la humedad del cuarto
  var temperatura;//la temperatura del cuarto
  var grados; //los grados que habrá en el cuarto
  
    database.ref().on("value", function(snap){ //empiezo a escuchar informacion de la base de datos
      //tomo los valores que hay en mi base de datos
    ledStatus = snap.val().ledStatus;
    cerca = snap.val().cerca;
    humedad = snap.val().humedad;
    temperatura = snap.val().temperatura;
    grados = snap.val().temperatura;

    if(ledStatus == 1){ //si en la base de datos tengo 1, significa que seteare el html de la luz a prendido
      $(".lightStatus").text("Luz prendida");
    } else { //aqui significa que está apagado
      $(".lightStatus").text("Luz apagada");
    }

        document.getElementById("temp").innerHTML = temperatura; //seteo el elemento de html a lo de mi base de datos
        document.getElementById("hum").innerHTML = humedad; //seteo el elemento de mi html a lo de mi base de datos

    if(cerca==1){ //si detecto a alguien, escribo verdadero en mi html
            document.getElementById("cerca").innerHTML = "Verdadero";

    }else{ //si no, escribo falso
            document.getElementById("cerca").innerHTML = "Falso";
    }

      
    if(ledStatus == 90){ //si en la base de datos tengo 1, significa que seteare el html de la luz a prendido
      $(".grados").text("90");
    } else { //aqui significa que está apagado
      $(".grados").text("0");
    }
  });

  $(".lightButton").click(function(){ //cuando le doy click a mi boton del led
    //le digo que obtenga la informacion de firebase, porque quiero setear un dato a base de mi boton
    var firebaseRef = firebase.database().ref().child("ledStatus");

    //si oprimi el boton y tenia 1, significa que lo estoy apagando e igualo el valor a 0
    if(ledStatus == 1){
      firebaseRef.set(0);
      ledStatus = 0;
    } else { //en otro caso significa que lo estoy prendiendo
      firebaseRef.set(1);
      ledStatus = 1;
    }
    
  });
    $(".botonGrados").click(function(){ //cuando le doy click a mi boton de cambiar grados

    var firebaseRef2 = firebase.database().ref().child("grados");

       if(grados == 90){
      firebaseRef2.set(0);
      grados = 0;
    } else { 
      firebaseRef2.set(90);
      grados = 90;
    }    
  });

});
