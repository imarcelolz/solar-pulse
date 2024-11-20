class Status:
    pass

class ApiClient:
    api_key: str = ''
    installation_id: str = ''

    def __init__(self, api_key: str, installation_id: str):
        self.api_key = api_key
        self.installation_id = installation_id

    def battery(self) -> Status:
        return Status()

    def generator(self) -> Status:
        return Status()

    def solar(self) -> Status:
        return Status()