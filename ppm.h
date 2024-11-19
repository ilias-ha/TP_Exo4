#ifndef PPM_H
#define PPM_H

/**
 * @file ppm.h
 * @brief Déclarations et fonctions utilitaires pour manipuler des images au format PPM.
 *
 * Ce fichier définit des structures et des fonctions pour créer, manipuler
 * et exporter des images au format PPM (Portable Pixmap Format).
 * Il offre une abstraction simple pour gérer des images couleur (RGB).
 */

/**
 * @struct ppm_pixel
 * @brief Représente un pixel d'une image PPM.
 *
 * Les valeurs des composantes rouge (r), verte (g), et bleue (b)
 * sont stockées sous forme de valeurs non signées sur 8 bits.
 */
struct ppm_pixel {
  unsigned char r; /**< Composante rouge du pixel. */
  unsigned char g; /**< Composante verte du pixel. */
  unsigned char b; /**< Composante bleue du pixel. */
};

/**
 * @brief Initialise un pixel avec des valeurs de couleur.
 *
 * @param px Pointeur vers le pixel à initialiser.
 * @param r Composante rouge du pixel (0-255).
 * @param g Composante verte du pixel (0-255).
 * @param b Composante bleue du pixel (0-255).
 */
static inline void ppm_setpixel(struct ppm_pixel *px, unsigned char r,
                                unsigned char g, unsigned char b) {
  px->r = r;
  px->g = g;
  px->b = b;
}

/**
 * @struct ppm_image
 * @brief Représente une image PPM.
 *
 * Contient les dimensions de l'image (largeur et hauteur) et un tableau
 * dynamique de pixels.
 */
struct ppm_image {
  unsigned int width;  /**< Largeur de l'image. */
  unsigned int height; /**< Hauteur de l'image. */
  struct ppm_pixel *px; /**< Tableau dynamique de pixels. */
};

/**
 * @brief Initialise une image PPM avec une largeur et une hauteur spécifiques.
 *
 * Alloue la mémoire nécessaire pour les pixels.
 *
 * @param im Pointeur vers la structure ppm_image à initialiser.
 * @param w Largeur de l'image en pixels.
 * @param h Hauteur de l'image en pixels.
 * @return 0 en cas de succès, 1 en cas d'erreur (ex. : allocation échouée).
 */
int ppm_image_init(struct ppm_image *im, int w, int h);

/**
 * @brief Libère les ressources associées à une image PPM.
 *
 * Libère la mémoire allouée pour les pixels et réinitialise la structure.
 *
 * @param im Pointeur vers la structure ppm_image à libérer.
 * @return 0 en cas de succès, 1 si l'image est déjà libérée ou invalide.
 */
int ppm_image_release(struct ppm_image *im);

/**
 * @brief Définit un pixel d'une image PPM à des coordonnées spécifiques.
 *
 * @param im Pointeur vers la structure ppm_image.
 * @param x Coordonnée horizontale (colonne) du pixel (0 = x < largeur).
 * @param y Coordonnée verticale (ligne) du pixel (0 = y < hauteur).
 * @param r Composante rouge du pixel (0-255).
 * @param g Composante verte du pixel (0-255).
 * @param b Composante bleue du pixel (0-255).
 */
static inline void ppm_image_setpixel(struct ppm_image *im, int x, int y,
                                      unsigned char r, unsigned char g,
                                      unsigned char b) {
  struct ppm_pixel *px = im->px + im->width * y + x;
  ppm_setpixel(px, r, g, b);
}

/**
 * @brief Exporte une image PPM vers un fichier au format PPM.
 *
 * @param im Pointeur vers la structure ppm_image à exporter.
 * @param path Chemin du fichier de sortie.
 * @return 0 en cas de succès, 1 en cas d'erreur (ex. : fichier inaccessible).
 */
int ppm_image_dump(struct ppm_image *im, char *path);

#endif /* PPM_H */

