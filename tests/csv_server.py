from io import BytesIO
import pandas as pd
import socketserver

HOST, PORT = "localhost", 11111
BUFFER_SIZE = 1024


class CSVHandler(socketserver.BaseRequestHandler):
    def __init__(self, request, client_address, server):
        self.byte_buffer = b''
        self.df = pd.DataFrame()
        super(CSVHandler, self).__init__(request, client_address, server)

    def handle(self) -> None:
        self.data = b''
        while True: 
            self.data = self.request.recv(BUFFER_SIZE)
            if not self.data: 
                break
            else: 
                self.byte_buffer += self.data
        self.df = pd.read_csv(BytesIO(self.byte_buffer))
        print(self.df)


if __name__ == "__main__":
    with socketserver.TCPServer((HOST, PORT), CSVHandler) as server:
        print(f"Server is running on {HOST} port {PORT}")
        server.serve_forever()
