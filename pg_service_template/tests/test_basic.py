import pytest

from testsuite.databases import pgsql

# Start the tests via `make test-debug` or `make test-release`

async def test_first_time_users(service_client):
    response = await service_client.post(
        '/v1/hello',
        params={'name': 'userver'},
    )
    assert response.status == 200
    assert response.text == 'Hello, userver!\n'


async def test_db_updates(service_client):
    response = await service_client.post('/todo_list', params={'name': 'World'})
    assert response.status == 200
    assert response.text == 'Hello, World!\n'

    response = await service_client.post('/v1/hello', params={'name': 'World'})
    assert response.status == 200
    assert response.text == 'Hi again, World!\n'

    response = await service_client.post('/v1/hello', params={'name': 'World'})
    assert response.status == 200
    assert response.text == 'Hi again, World!\n'


@pytest.mark.pgsql('db_1', files=['initial_data.sql'])
async def test_db_initial_data(service_client):
    response = await service_client.post(
        '/v1/hello',
        params={'name': 'user-from-initial_data.sql'},
    )
    assert response.status == 200
    assert response.text == 'Hi again, user-from-initial_data.sql!\n'

import unittest


def test_add_note(self):
    response = self.client.add_note("Buy milk")
    self.assertTrue(response['success'])
    self.assertIn('id', response)

def test_get_note(self):
    add_response = self.client.add_note("Read a book")
    note_id = add_response['id']
    get_response = self.client.get_note(note_id)
    self.assertEqual(get_response['text'], "Read a book")

def test_update_note(self):
    add_response = self.client.add_note("Go running")
    note_id = add_response['id']
    update_response = self.client.update_note(note_id, "Go swimming")
    self.assertTrue(update_response['success'])

def test_delete_note(self):
    add_response = self.client.add_note("Call Alice")
    note_id = add_response['id']
    delete_response = self.client.delete_note(note_id)
    self.assertTrue(delete_response['success'])

def test_list_notes(self):
    self.client.add_note("Buy bread")
    self.client.add_note("Study for exams")
    list_response = self.client.list_notes()
    self.assertTrue(len(list_response) >= 2)
    self.assertIn("Buy bread", [note['text'] for note in list_response])
    self.assertIn("Study for exams", [note['text'] for note in list_response])
