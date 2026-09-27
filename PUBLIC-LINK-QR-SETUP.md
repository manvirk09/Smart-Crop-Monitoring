# Public Link + QR Setup

## Important limitation

The live Wokwi sensor connection uses `127.0.0.1` (your own computer). A public static website can open the dashboard, but it cannot directly connect to your local Wokwi bridge from another person's phone or PC.

So there are two useful sharing modes:

1. **Public dashboard link/QR:** anyone can open the dashboard. It will use DEMO DATA unless a compatible public backend is added.
2. **Live local demo:** on your computer, Wokwi + `bridge.py` + the local web server provide real SENSOR DATA.

## GitHub Pages setup

1. Create a GitHub repository, for example `smart-crop-monitoring`.
2. Upload `index.html` to the repository root.
3. Open the repository's **Settings → Pages**.
4. Under **Build and deployment**, choose **Deploy from a branch**.
5. Select your main branch and `/ (root)`.
6. Save.
7. GitHub will publish the site. The URL will look like:
   `https://YOUR-USERNAME.github.io/smart-crop-monitoring/`

GitHub Pages can host static HTML/CSS/JavaScript files directly from a repository.

## QR code

After the GitHub Pages URL exists, generate a QR code from that exact URL using any trusted QR-code generator, then put the QR on your project poster/presentation.

Do not generate the final QR until the public URL is known, because the QR encodes the URL.

## Live SENSOR DATA over the internet

That requires a separate public WebSocket/backend or a secure tunnel from your computer. The current project intentionally keeps the Wokwi bridge on localhost for the working local demo.
