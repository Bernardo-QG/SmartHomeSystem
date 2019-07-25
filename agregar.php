
<?php


$username = $_POST['name'];
$pass = $_POST['password'];



		$conn = mysqli_connect('localhost','id10249898_ing_software','contrasena','id10249898_smartapp');
			if (mysqli_connect_errno()){
				echo "Error de conexión: ".mysqli_connect_errno();
			}

		$agregar = mysqli_query($conn,"insert into usuario (name, password) values ('$username', '$pass')");

		
		mysqli_close($conn);

?>