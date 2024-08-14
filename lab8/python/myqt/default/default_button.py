from PyQt6.QtWidgets import *


class Button(QPushButton):
    def __init__(self, name: str):
        super().__init__(name)
        self.setFixedWidth(500)
        self.setFixedHeight(50)

    def on_click(self, func: callable):
        self.clicked.connect(func)
