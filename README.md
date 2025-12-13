# YtStats 📊📺

**YtStats** is a privacy-focused WebAssembly application built with Qt 6 & QML. It analyzes your personal YouTube watch history to generate detailed statistics about your viewing habits without ever sending your data to a server.

> **Privacy Note:** This application runs entirely in your browser (Client-Side). Your Google Takeout data is processed locally on your machine and is **never** uploaded to any external server.

## ✨ Features

* **📈 Watch Time Analysis:** Calculate exactly how much time you've spent watching videos (total and per year).
* **🏆 Top Channels:** Discover which creators you watch the most.
* **🎬 Top Videos:** See your most re-watched videos of all time.
* **📅 Yearly Recap:** Generate a "Spotify Wrapped" style summary for your YouTube usage.
* **📂 Format Support:** Supports both JSON and HTML history files from Google Takeout.
* **🚀 High Performance:** Powered by C++ and WebAssembly for fast processing of large history files.

## 🛠️ Tech Stack

* **Framework:** Qt 6.8 (QML & C++)
* **Platform:** WebAssembly (WASM)
* **Build System:** CMake
* **Compiler:** Emscripten

---

## 🏗️ Build Instructions

### Prerequisites

To build this project, you need a Linux environment (tested on Fedora 42) with the following installed:

1.  **System Dependencies:** `cmake`, `ninja-build`, `python3`
2.  **Qt 6.8 (Target):** The WebAssembly (Multithreaded) binaries.
3.  **Qt 6.8 (Host):** The Linux Desktop (`gcc_64`) binaries (Required for QML compilation tools).
4.  **Emscripten SDK:** Version matching your Qt release (e.g., v3.1.56 for Qt 6.8).

### 1. Environment Setup

Ensure your **Emscripten** environment is active:
```bash
# Adjust path to your emsdk installation
source ~/emsdk/emsdk_env.sh
```

### 2. Compilation
Since this is a cross-compiled project, you must point CMake to your Host Qt installation using QT_HOST_PATH.



#### 1. Clone the repository
```bash
git clone [https://github.com/Rob1d/YtStats](https://github.com/Rob1d/YtStats.git)
cd YtStats
```

#### 2. Create build directory
```bash
mkdir build-wasm
cd build-wasm
```
#### 3. Configure with CMake

##### REPLACE PATHS with your actual Qt locations
```bash
~/Qt/6.8.0/wasm_multithread/bin/qt-cmake \
  -DQT_HOST_PATH=~/Qt/6.8.0/gcc_64 \
  ..
```
#### 4. Build the project
cmake --build .
🚀 How to Run
Because this project uses multithreading, browsers require specific security headers (SharedArrayBuffer support). You cannot simply open the .html file.

Local Development Server
Create a file named server.py in your build directory:

```Python

from http.server import HTTPServer, SimpleHTTPRequestHandler
import sys

class SecurityHeaderHandler(SimpleHTTPRequestHandler):
    def end_headers(self):
        self.send_header("Cross-Origin-Opener-Policy", "same-origin")
        self.send_header("Cross-Origin-Embedder-Policy", "require-corp")
        super().end_headers()

    def do_GET(self):
        if self.path.endswith('.wasm'):
            self.send_header("Content-Type", "application/wasm")
        super().do_GET()

if __name__ == '__main__':
    port = 8000
    print(f"Serving at http://localhost:{port}")
    HTTPServer(('localhost', port), SecurityHeaderHandler).serve_forever()

```
Run the server:

```Bash

python3 server.py
```
Open your browser to http://localhost:8000/YtStats.html.

# 📥 How to Get Your Data

To use YtStats, you need your history file from Google:

Go to Google Takeout.

Deselect all, then find and select YouTube and YouTube Music.

Click "All YouTube data included" and select only "history".

Click "Multiple formats" and ensure History is set to JSON (preferred) or HTML.

Proceed to export and download the ZIP file.

Extract the ZIP and load watch-history.json into YtStats.

# ☁️ Deployment
If hosting on Netlify, Vercel, or Cloudflare Pages, ensure you add the following headers to your configuration to enable multithreading:

```Plaintext

Cross-Origin-Opener-Policy: same-origin
Cross-Origin-Embedder-Policy: require-corp
```

# 📄 License
This project is licensed under the MIT License - see the LICENSE file for details.