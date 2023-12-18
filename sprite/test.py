from PIL import Image, ImageDraw, ImageFont

def add_red_lines_with_variable_font_size(image_path, output_path, interval=16):
    """
    Ajoute des lignes rouges verticales à une image à un intervalle spécifié et écrit un numéro sur chaque ligne.
    Réduit la taille de la police lorsque le numéro atteint 100.

    :param image_path: Chemin vers l'image d'entrée.
    :param output_path: Chemin pour sauvegarder l'image modifiée.
    :param interval: Intervalle en pixels entre chaque ligne rouge.
    """
    # Ouvrir l'image
    with Image.open(image_path) as img:
        draw = ImageDraw.Draw(img)

        # Obtenir la largeur et la hauteur de l'image
        width, height = img.size

        # Définir les polices
        default_font = ImageFont.load_default()
        small_font = ImageFont.truetype("Arial.TTF", 9)  # Utiliser une police plus petite

        # Dessiner des lignes rouges et écrire des numéros
        for i, x in enumerate(range(0, width, interval)):
            draw.line((x, 0, x, height), fill="red")

            # Choisir la police en fonction du numéro
            font = small_font if i >= 100 else default_font
            draw.text((x + 2, 0), str(i), fill="black", font=font)

        # Sauvegarder l'image modifiée
        img.save(output_path)

# Exemple d'utilisation
image_path = "./SuperMarioBrosMap1-1.png"  # Remplacer par votre chemin d'image
output_path = "modified_image.png"      # Remplacer par votre chemin de sortie souhaité

# Ajouter des lignes rouges et des numéros à l'image
add_red_lines_with_variable_font_size(image_path, output_path)

