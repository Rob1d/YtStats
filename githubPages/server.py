#! /usr/bin/env python3

from http.server import HTTPServer, SimpleHTTPRequestHandler
import sys

class SecurityHeaderHandler(SimpleHTTPRequestHandler):
    def end_headers(self):
        # These two headers unlock SharedArrayBuffer
        self.send_header("Cross-Origin-Opener-Policy", "same-origin")
        self.send_header("Cross-Origin-Embedder-Policy", "require-corp")
        super().end_headers()

if __name__ == '__main__':
    port = 8000
    print(f"Serving on http://localhost:{port} with COOP/COEP headers...")
    httpd = HTTPServer(('localhost', port), SecurityHeaderHandler)
    try:
        httpd.serve_forever()
    except KeyboardInterrupt:
        pass
