def registrar_usuario():
    nombre = input("Nombre completo: ").strip()
    correo = input("Correo: ").strip()
    clave = input("Clave: ").strip()
    if not nombre or not correo or not clave:
        print("Todos los campos son obligatorios.")
        return
    with open("usuarios.txt", "a") as f:
        f.write(f"{correo},{clave},{nombre}\n")
    print("Usuario registrado.")

registrar_usuario()