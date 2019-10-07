from django.http import HttpResponse
from django.contrib.auth import authenticate, login


def index(request):
    return HttpResponse("Hello, world. You're at the auth index.")


def login_view(request):
    username = request.POST['username']
    password = request.POST['password']
    user = authenticate(request, username=username, password=password)
    if user is not None:
        login(request, user)
        # Redirect to a success page.
        return HttpResponse("login success")
    else:
        # Return an 'invalid login' error message.
        return HttpResponse("invalid login")
